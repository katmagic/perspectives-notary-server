/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIObjectOutputStre">
 **/

package org.mozilla.xpcom;

public interface nsIObjectOutputStream extends nsIBinaryOutputStream
{
  public static final String NS_IOBJECTOUTPUTSTREAM_IID =
    "{92c898ac-5fde-4b99-87b3-5d486422094b}";

  public void writeObject(nsISupports arg1, boolean arg2);

  public void writeSingleRefObject(nsISupports arg1);

  public void writeCompoundObject(nsISupports arg1, String arg2, boolean arg3);

  public void writeID(String arg1);

}
