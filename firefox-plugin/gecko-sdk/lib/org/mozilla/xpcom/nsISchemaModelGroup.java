/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISchemaModelGroup">
 **/

package org.mozilla.xpcom;

public interface nsISchemaModelGroup extends nsISchemaParticle
{
  public static final String NS_ISCHEMAMODELGROUP_IID =
    "{3c14a02a-6f4e-11d5-9b46-000064657374}";

  public static final int COMPOSITOR_ALL = 1;

  public static final int COMPOSITOR_SEQUENCE = 2;

  public static final int COMPOSITOR_CHOICE = 3;

  public int getCompositor();

  public long getParticleCount();

  public nsISchemaParticle getParticle(long arg1);

  public nsISchemaElement getElementByName(String arg1);

}
