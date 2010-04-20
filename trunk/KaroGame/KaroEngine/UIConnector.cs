using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;

namespace Karo
{
    public class UIConnector
    {

        /// <summary>
        /// Overload the function so it will return the correct Title, even when used as *.dll
        /// </summary>
        /// <returns>Engine title</returns>
        public override string ToString()
        {
            // Get Current Assembly
            Assembly asm = Assembly.GetExecutingAssembly();

            // Get Title
            AssemblyTitleAttribute titleAtt =
                (AssemblyTitleAttribute)Attribute.GetCustomAttribute(asm,
                    typeof(AssemblyTitleAttribute));

            return titleAtt.Title.ToString();
        }

        /// <summary>
        /// Returns the version number of the *.dll
        /// </summary>
        /// <returns>Versionnumber as string</returns>
        public string GetVersionNumber()
        {
            // Get Current Assembly
            Assembly asm = Assembly.GetExecutingAssembly();

            // Return version number
            return asm.GetName().Version.ToString();
        }
    }
}
