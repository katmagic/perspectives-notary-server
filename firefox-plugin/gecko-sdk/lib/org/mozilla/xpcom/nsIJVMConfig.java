/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIJVMConfig">
 **/

package org.mozilla.xpcom;

public interface nsIJVMConfig extends nsISupports
{
  public static final String NS_IJVMCONFIG_IID =
    "{3e333e20-b190-42d8-b993-d5fa435e46c4}";

  public String getVersion();

  public String getType();

  public String getOS();

  public String getArch();

  public nsIFile getPath();

  public nsIFile getMozillaPluginPath();

  public String getDescription();

}
