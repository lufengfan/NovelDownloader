﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Web;
using HtmlAgilityPack;
using NovelDownloader.Token;
using SamLu.Web;

namespace NovelDownloader.Plugin.顶点小说
{
	public class ChapterToken : NDTChapter
	{
		internal static readonly Regex ChapterUrlRegex = new Regex(@"http://www.23us.com/html/\d*/(?<BookUnicode>\d*)/(?<ChapterUnicode>\d*).html", RegexOptions.Compiled);

		public override string Type { get; protected set; } = "章节";

		public ulong ChapterUnicode { get; private set; }

		public ChapterToken(Uri uri) : base(uri)
		{
			if (uri == null) throw new ArgumentNullException(nameof(uri));
			string url = uri.ToString();

			Match m = ChapterToken.ChapterUrlRegex.Match(url);
			if (m.Success)
			{
				this.ChapterUnicode = ulong.Parse(m.Groups["ChapterUnicode"].Value);
				this.ChapterUrl = url;
			}
			else
				throw new InvalidOperationException(
					"无法解析URL。",
					new ArgumentOutOfRangeException(nameof(url), url, "URL不符合格式。"));
		}

		/// <summary>
		/// 初始化<see cref="ChapterToken"/>对象。
		/// </summary>
		public ChapterToken() : base() { }

		public ChapterToken(string url) : this(new Uri(url)) { }

		public ChapterToken(string title, string description) : base(title, description) { }

		internal string ChapterUrl { get; set; }

		private int index;
		private string chapterContentHTML;

		#region StartCreep
		protected override bool CanStartCreep()
		{
			if ((this.ChapterUrl == null) || !ChapterToken.ChapterUrlRegex.IsMatch(this.ChapterUrl)) return false;

			try
			{
				HtmlDocument doc = new HtmlDocument();
				doc.LoadHtml(HTML.GetSource(this.ChapterUrl, Encoding.GetEncoding("GBK")));

				HtmlNode contentNode = doc.GetElementbyId("contents");
				if (contentNode == null) return false;

				this.chapterContentHTML = contentNode.InnerHtml;
			}
			catch (Exception e)
			{
				this.OnCreepErrored(this, e);
				return false;
			}

			return true;
		}

		protected override void StartCreepInternal()
		{
			this.ChapterUnicode = ulong.Parse(ChapterToken.ChapterUrlRegex.Match(this.ChapterUrl).Groups["ChapterUnicode"].Value);
		}
		#endregion

		#region Creep
		private bool CanCreep(int index)
		{
			return (index < this.chapterContentHTML.Length);
		}

		protected override bool CanCreep<TData>(TData data)
		{
			if (typeof(TData).Equals(typeof(int)))
				return this.CanCreep((int)(object)data);
			else
				throw new NotSupportedException(
					string.Format("不支持的数据类型{0}", typeof(TData).FullName),
					new ArgumentException(
						string.Format("参数的类型为{1}。", typeof(TData).FullName),
						nameof(data)
					)
				);
		}

		private string Creep()
		{
			const string SEPERATOR = "<br>";

			int start_index = this.index;
			int end_index = this.chapterContentHTML.IndexOf(SEPERATOR, index) - 1;
			if (end_index == -2)
			{
				end_index = this.chapterContentHTML.Length - 1;
				this.index = end_index + 1;
			}
			else
			{
				this.index = end_index + SEPERATOR.Length + 1;
			}

			string line = this.chapterContentHTML.Substring(start_index, end_index - start_index + 1);

			return line;
		}

		public override TFetch Creep<TData, TFetch>(TData data)
		{
			if (typeof(TFetch).Equals(typeof(string)))
			{
				return (TFetch)(object)this.Creep();
			}
			else
			{
				if (!typeof(TFetch).Equals(typeof(string)))
					throw new NotSupportedException(
						string.Format("不支持的数据类型{0}", typeof(TFetch).FullName)
					);
			}

			throw new InvalidOperationException();
		}

		protected override bool CreepInternal()
		{
			if (!this.CanCreep(this.index)) return false;

			string data = HttpUtility.HtmlDecode((this.Creep()).Replace("<br />", Environment.NewLine)).Trim();
			if (data != string.Empty)
			{
				this.Add(new TextToken(data));
				this.OnCreepFetched(this, data);
			}
			return true;
		}
		#endregion
	}
}
