/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISchemaUnionType">
 **/

package org.mozilla.xpcom;

public interface nsISchemaUnionType extends nsISchemaSimpleType
{
  public static final String NS_ISCHEMAUNIONTYPE_IID =
    "{3c14a026-6f4e-11d5-9b46-000064657374}";

  public long getUnionTypeCount();

  public nsISchemaSimpleType getUnionType(long arg1);

}
