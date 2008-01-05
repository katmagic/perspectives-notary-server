/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISchemaParticle">
 **/

package org.mozilla.xpcom;

public interface nsISchemaParticle extends nsISchemaComponent
{
  public static final String NS_ISCHEMAPARTICLE_IID =
    "{3c14a029-6f4e-11d5-9b46-000064657374}";

  public static final int PARTICLE_TYPE_ELEMENT = 1;

  public static final int PARTICLE_TYPE_MODEL_GROUP = 2;

  public static final int PARTICLE_TYPE_ANY = 3;

  public static final long OCCURRENCE_UNBOUNDED = 4294967295L;

  public String getName();

  public int getParticleType();

  public long getMinOccurs();

  public long getMaxOccurs();

}
