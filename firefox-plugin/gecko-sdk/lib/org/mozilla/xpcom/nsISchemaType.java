/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISchemaType">
 **/

package org.mozilla.xpcom;

public interface nsISchemaType extends nsISchemaComponent
{
  public static final String NS_ISCHEMATYPE_IID =
    "{3c14a022-6f4e-11d5-9b46-000064657374}";

  public static final int SCHEMA_TYPE_SIMPLE = 1;

  public static final int SCHEMA_TYPE_COMPLEX = 2;

  public static final int SCHEMA_TYPE_PLACEHOLDER = 3;

  public String getName();

  public int getSchemaType();

}
