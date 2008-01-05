/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISerializable">
 **/

package org.mozilla.xpcom;

public interface nsISerializable extends nsISupports
{
  public static final String NS_ISERIALIZABLE_IID =
    "{91cca981-c26d-44a8-bebe-d9ed4891503a}";

  public void read(nsIObjectInputStream arg1);

  public void write(nsIObjectOutputStream arg1);

}
