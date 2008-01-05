/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISchemaAttributeG">
 **/

package org.mozilla.xpcom;

public interface nsISchemaAttributeGroup extends nsISchemaAttributeComponent
{
  public static final String NS_ISCHEMAATTRIBUTEGROUP_IID =
    "{3c14a02f-6f4e-11d5-9b46-000064657374}";

  public long getAttributeCount();

  public nsISchemaAttributeComponent getAttributeByIndex(long arg1);

  public nsISchemaAttributeComponent getAttributeByName(String arg1);

}
