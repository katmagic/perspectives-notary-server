/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIUpdate">
 **/

package org.mozilla.xpcom;

public interface nsIUpdate extends nsISupports
{
  public static final String NS_IUPDATE_IID =
    "{b0fb539e-f4ab-4ea1-bd75-e6d2813e5fc1}";

  public String getType();

  public void setType(String arg1);

  public String getName();

  public void setName(String arg1);

  public String getVersion();

  public void setVersion(String arg1);

  public String getExtensionVersion();

  public void setExtensionVersion(String arg1);

  public String getBuildID();

  public void setBuildID(String arg1);

  public String getDetailsURL();

  public void setDetailsURL(String arg1);

  public String getLicenseURL();

  public void setLicenseURL(String arg1);

  public String getServiceURL();

  public void setServiceURL(String arg1);

  public boolean getIsCompleteUpdate();

  public void setIsCompleteUpdate(boolean arg1);

  public boolean getIsSecurityUpdate();

  public void setIsSecurityUpdate(boolean arg1);

  public long getInstallDate();

  public void setInstallDate(long arg1);

  public String getStatusText();

  public void setStatusText(String arg1);

  public nsIUpdatePatch getSelectedPatch();

  public String getState();

  public void setState(String arg1);

  public int getErrorCode();

  public void setErrorCode(int arg1);

  public long getPatchCount();

  public nsIUpdatePatch getPatchAt(long arg1);

  public nsIDOMElement serialize(nsIDOMDocument arg1);

}
