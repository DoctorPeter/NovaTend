using System.ComponentModel;

namespace SystemData.Common
{
    /// <summary>
    /// Base class for data model.
    /// </summary>
    public class ModelBase : INotifyPropertyChanged
    {
        #region INotifyPropertyChanged members
        protected void RaisePropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
        }

        public event PropertyChangedEventHandler PropertyChanged;
        #endregion
    }

}
