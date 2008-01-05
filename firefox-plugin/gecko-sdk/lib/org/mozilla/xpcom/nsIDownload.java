/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDownload">
 **/

package org.mozilla.xpcom;

public interface nsIDownload extends nsITransfer
{
  public static final String NS_IDOWNLOAD_IID =
    "{9e1fd9f2-9727-4926-85cd-f16c375bba6d}";

  public nsILocalFile getTargetFile();

  public int getPercentComplete();

  public double getAmountTransferred();

  public double getSize();

  public nsIURI getSource();

  public nsIURI getTarget();

  public nsICancelable getCancelable();

  public String getDisplayName();

  public long getStartTime();

  public nsIMIMEInfo getMIMEInfo();

}
