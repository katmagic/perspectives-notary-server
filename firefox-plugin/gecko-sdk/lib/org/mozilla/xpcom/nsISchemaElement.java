/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISchemaElement">
 **/

package org.mozilla.xpcom;

public interface nsISchemaElement extends nsISchemaParticle
{
  public static final String NS_ISCHEMAELEMENT_IID =
    "{3c14a02c-6f4e-11d5-9b46-000064657374}";

  public nsISchemaType getType();

  public String getDefaultValue();

  public String getFixedValue();

  public boolean getNillable();

  public boolean getAbstract();

}
