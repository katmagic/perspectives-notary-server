/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIUpdatePatch">
 **/

package org.mozilla.xpcom;

public interface nsIUpdatePatch extends nsISupports
{
  public static final String NS_IUPDATEPATCH_IID =
    "{56863a67-bd69-42de-9f40-583e625b457d}";

  public String getType();

  public void setType(String arg1);

  public String getURL();

  public void setURL(String arg1);

  public String getHashFunction();

  public void setHashFunction(String arg1);

  public String getHashValue();

  public void setHashValue(String arg1);

  public long getSize();

  public void setSize(long arg1);

  public String getState();

  public void setState(String arg1);

  public boolean getSelected();

  public void setSelected(boolean arg1);

  public nsIDOMElement serialize(nsIDOMDocument arg1);

}
