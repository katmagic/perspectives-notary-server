/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISchemaAnyParticl">
 **/

package org.mozilla.xpcom;

public interface nsISchemaAnyParticle extends nsISchemaParticle
{
  public static final String NS_ISCHEMAANYPARTICLE_IID =
    "{3c14a02b-6f4e-11d5-9b46-000064657374}";

  public static final int PROCESS_STRICT = 1;

  public static final int PROCESS_SKIP = 2;

  public static final int PROCESS_LAX = 3;

  public int getProcess();

  public String getNamespace();

}
