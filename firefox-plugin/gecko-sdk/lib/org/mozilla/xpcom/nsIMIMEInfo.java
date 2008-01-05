/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIMIMEInfo">
 **/

package org.mozilla.xpcom;

public interface nsIMIMEInfo extends nsISupports
{
  public static final String NS_IMIMEINFO_IID =
    "{1448b42f-cf0d-466e-9a15-64e876ebe857}";

  public static final int saveToDisk = 0;

  public static final int alwaysAsk = 1;

  public static final int useHelperApp = 2;

  public static final int handleInternally = 3;

  public static final int useSystemDefault = 4;

  public nsIUTF8StringEnumerator getFileExtensions();

  public void setFileExtensions(String arg1);

  public boolean extensionExists(String arg1);

  public void appendExtension(String arg1);

  public String getPrimaryExtension();

  public void setPrimaryExtension(String arg1);

  public String getMIMEType();

  public String getDescription();

  public void setDescription(String arg1);

  public long getMacType();

  public void setMacType(long arg1);

  public long getMacCreator();

  public void setMacCreator(long arg1);

  public boolean equals(nsIMIMEInfo arg1);

  public nsIFile getPreferredApplicationHandler();

  public void setPreferredApplicationHandler(nsIFile arg1);

  public String getApplicationDescription();

  public void setApplicationDescription(String arg1);

  public boolean getHasDefaultHandler();

  public String getDefaultDescription();

  public void launchWithFile(nsIFile arg1);

  public int getPreferredAction();

  public void setPreferredAction(int arg1);

  public boolean getAlwaysAskBeforeHandling();

  public void setAlwaysAskBeforeHandling(boolean arg1);

}
