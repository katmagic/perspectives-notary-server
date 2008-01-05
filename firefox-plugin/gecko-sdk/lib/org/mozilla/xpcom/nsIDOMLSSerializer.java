/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMLSSerializer">
 **/

package org.mozilla.xpcom;

public interface nsIDOMLSSerializer extends nsISupports
{
  public static final String NS_IDOMLSSERIALIZER_IID =
    "{96ea4792-d362-4c28-a8c2-0337790d648a}";

  public nsIDOMDOMConfiguration getDomConfig();

  public String getNewLine();

  public void setNewLine(String arg1);

  public nsIDOMLSSerializerFilter getFilter();

  public void setFilter(nsIDOMLSSerializerFilter arg1);

  public boolean write(nsIDOMNode arg1, nsIDOMLSOutput arg2);

  public boolean writeToURI(nsIDOMNode arg1, String arg2);

  public String writeToString(nsIDOMNode arg1);

}
