/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDocumentCharsetI">
 **/

package org.mozilla.xpcom;

public interface nsIDocumentCharsetInfo extends nsISupports
{
  public static final String NS_IDOCUMENTCHARSETINFO_IID =
    "{2d40b291-01e1-11d4-9d0e-0050040007b2}";

  public nsIAtom getForcedCharset();

  public void setForcedCharset(nsIAtom arg1);

  public boolean getForcedDetector();

  public void setForcedDetector(boolean arg1);

  public nsIAtom getParentCharset();

  public void setParentCharset(nsIAtom arg1);

  public int getParentCharsetSource();

  public void setParentCharsetSource(int arg1);

}
