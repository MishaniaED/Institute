using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Validator
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            
        }

        public static DependencyProperty StyleOfTextFieldProperty =
    DependencyProperty.Register(nameof(StyleOfTextField), typeof(Style),
        typeof(MainWindow), new UIPropertyMetadata(StyleGrayByDefault()));

        public Style StyleOfTextField
        {
            get =>
                (Style)GetValue(StyleOfTextFieldProperty);

            set =>
                SetValue(StyleOfTextFieldProperty, value);

        }

        private static Style StyleGrayByDefault()
        {
            Style bStyleTmp = new Style();
            bStyleTmp.Setters.Add(new Setter
            { Property = BackgroundProperty, Value = new SolidColorBrush(Colors.LightGray) });
            bStyleTmp.Setters.Add(new Setter
            { Property = ForegroundProperty, Value = new SolidColorBrush(Colors.Gray) });
/*            bStyleTmp.Setters.Add(new Setter
            { Property = MarginProperty, Value = new Thickness(5) });*/
            bStyleTmp.Setters.Add(new Setter
            { Property = BorderBrushProperty, Value = new SolidColorBrush(Colors.Gray) });
            bStyleTmp.Setters.Add(new Setter
            { Property = FontFamilyProperty, Value = new FontFamily("Tadoma") });
            return bStyleTmp;
        }
    }
}
