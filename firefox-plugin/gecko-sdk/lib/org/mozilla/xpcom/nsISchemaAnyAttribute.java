/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISchemaAnyAttribu">
 **/

package org.mozilla.xpcom;

public interface nsISchemaAnyAttribute extends nsISchemaAttributeComponent
{
  public static final String NS_ISCHEMAANYATTRIBUTE_IID =
    "{3c14a030-6f4e-11d5-9b46-000064657374}";

  public static final int PROCESS_STRICT = 1;

  public static final int PROCESS_SKIP = 2;

  public static final int PROCESS_LAX = 3;

  public int getProcess();

  public String getNamespace();

}
