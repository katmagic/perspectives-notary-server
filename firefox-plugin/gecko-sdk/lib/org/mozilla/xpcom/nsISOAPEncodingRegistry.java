/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISOAPEncodingRegi">
 **/

package org.mozilla.xpcom;

public interface nsISOAPEncodingRegistry extends nsISupports
{
  public static final String NS_ISOAPENCODINGREGISTRY_IID =
    "{9fe91a61-3048-40e3-99ef-e39ab946ae0b}";

  public nsISOAPEncoding getAssociatedEncoding(String arg1, boolean arg2);

  public nsISchemaCollection getSchemaCollection();

  public void setSchemaCollection(nsISchemaCollection arg1);

}
