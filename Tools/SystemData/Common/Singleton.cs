using System;
using System.Reflection;

namespace SystemData.Common
{
    /// <summary>
    /// generic Singleton<T> (thread safe with deffered initialization)
    /// </summary>
    /// <typeparam name="T">Singleton class</typeparam>
    public class Singleton<T> where T : class
    {
        /// <summary>
        /// private ctor is needed to protect from creation of class instance. 
        /// ctor will be called from private ctor of a derriced class
        /// </summary>
        protected Singleton() { }

        /// <summary>
        /// Fabric for deffered initialization of class instance
        /// </summary>
        /// <typeparam name="S"></typeparam>
        private sealed class SingletonCreator<S> where S : class
        {
            //using Reflection to create instance without public ctor
            private static readonly S instance = (S)typeof(S).GetConstructor(
                        BindingFlags.Instance | BindingFlags.NonPublic,
                        null,
                        new Type[0],
                        new ParameterModifier[0]).Invoke(null);

            public static S CreatorInstance
            {
                get { return instance; }
            }
        }

        private static object lockObj = new object();

        public static T Instance
        {
            get
            {
                lock (lockObj)
                {
                    return SingletonCreator<T>.CreatorInstance;
                }
            }
        }

    }
}

