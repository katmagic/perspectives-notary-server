/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIHistoryEntry">
 **/

package org.mozilla.xpcom;

public interface nsIHistoryEntry extends nsISupports
{
  public static final String NS_IHISTORYENTRY_IID =
    "{a41661d4-1417-11d5-9882-00c04fa02f40}";

  public nsIURI getURI();

  public String getTitle();

  public boolean getIsSubFrame();

}
