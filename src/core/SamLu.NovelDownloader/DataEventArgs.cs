﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SamLu.NovelDownloader
{
    /// <summary>
    /// <see cref="DataEventArgs{T}"/>是包含特定数据的事件参数的基类。
    /// </summary>
    /// <typeparam name="TData">特定数据类型。</typeparam>
    public class DataEventArgs<TData> : EventArgs
    {
        /// <summary>
        /// 获取事件参数中的数据。
        /// </summary>
        public TData Data { get; set; }

        /// <summary>
        /// 初始化<see cref=" DataEventArgs{T}"/>对象。
        /// </summary>
        public DataEventArgs() : base() { }

        /// <summary>
        /// 使用指定的数据初始化<see cref=" DataEventArgs{T}"/>对象。
        /// </summary>
        /// <param name="data">指定的数据。</param>
        public DataEventArgs(TData data) : this()
        {
            this.Data = data;
        }

#pragma warning disable CS1591 // 缺少对公共可见类型或成员的 XML 注释
        public static implicit operator TData(DataEventArgs<TData> e)
        {
            if (e == null) throw new ArgumentNullException(nameof(e));

            return e.Data;
        }

        public static implicit operator DataEventArgs<TData>(TData data)
        {
            return new DataEventArgs<TData>(data);
        }
#pragma warning restore CS1591 // 缺少对公共可见类型或成员的 XML 注释
    }
}
