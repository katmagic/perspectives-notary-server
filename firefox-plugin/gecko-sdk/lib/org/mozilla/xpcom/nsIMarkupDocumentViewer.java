/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIMarkupDocumentVi">
 **/

package org.mozilla.xpcom;

public interface nsIMarkupDocumentViewer extends nsISupports
{
  public static final String NS_IMARKUPDOCUMENTVIEWER_IID =
    "{18cbdb18-3917-42fd-9c4a-0b2112d41a6d}";

  public void scrollToNode(nsIDOMNode arg1);

  public float getTextZoom();

  public void setTextZoom(float arg1);

  public boolean getAuthorStyleDisabled();

  public void setAuthorStyleDisabled(boolean arg1);

  public String getDefaultCharacterSet();

  public void setDefaultCharacterSet(String arg1);

  public String getForceCharacterSet();

  public void setForceCharacterSet(String arg1);

  public String getHintCharacterSet();

  public void setHintCharacterSet(String arg1);

  public int getHintCharacterSetSource();

  public void setHintCharacterSetSource(int arg1);

  public String getPrevDocCharacterSet();

  public void setPrevDocCharacterSet(String arg1);

  public void sizeToContent();

  public short getBidiTextDirection();

  public void setBidiTextDirection(short arg1);

  public short getBidiTextType();

  public void setBidiTextType(short arg1);

  public short getBidiControlsTextMode();

  public void setBidiControlsTextMode(short arg1);

  public short getBidiNumeral();

  public void setBidiNumeral(short arg1);

  public short getBidiSupport();

  public void setBidiSupport(short arg1);

  public short getBidiCharacterSet();

  public void setBidiCharacterSet(short arg1);

  public long getBidiOptions();

  public void setBidiOptions(long arg1);

}
