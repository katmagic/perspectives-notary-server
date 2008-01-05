/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMNameList">
 **/

package org.mozilla.xpcom;

public interface nsIDOMNameList extends nsISupports
{
  public static final String NS_IDOMNAMELIST_IID =
    "{faaf1b80-1ddd-11d9-8c46-000a95dc234c}";

  public String getName(long arg1);

  public String getNamespaceURI(long arg1);

  public long getLength();

  public boolean contains(String arg1);

  public boolean containsNS(String arg1, String arg2);

}
