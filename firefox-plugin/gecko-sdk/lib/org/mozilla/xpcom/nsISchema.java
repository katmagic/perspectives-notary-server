/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISchema">
 **/

package org.mozilla.xpcom;

public interface nsISchema extends nsISchemaComponent
{
  public static final String NS_ISCHEMA_IID =
    "{3c14a021-6f4e-11d5-9b46-000064657374}";

  public String getSchemaNamespace();

  public long getTypeCount();

  public nsISchemaType getTypeByIndex(long arg1);

  public nsISchemaType getTypeByName(String arg1);

  public long getAttributeCount();

  public nsISchemaAttribute getAttributeByIndex(long arg1);

  public nsISchemaAttribute getAttributeByName(String arg1);

  public long getElementCount();

  public nsISchemaElement getElementByIndex(long arg1);

  public nsISchemaElement getElementByName(String arg1);

  public long getAttributeGroupCount();

  public nsISchemaAttributeGroup getAttributeGroupByIndex(long arg1);

  public nsISchemaAttributeGroup getAttributeGroupByName(String arg1);

  public long getModelGroupCount();

  public nsISchemaModelGroup getModelGroupByIndex(long arg1);

  public nsISchemaModelGroup getModelGroupByName(String arg1);

  public nsISchemaCollection getCollection();

}
