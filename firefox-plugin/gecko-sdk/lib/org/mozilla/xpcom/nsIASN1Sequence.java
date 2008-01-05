/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIASN1Sequence">
 **/

package org.mozilla.xpcom;

public interface nsIASN1Sequence extends nsIASN1Object
{
  public static final String NS_IASN1SEQUENCE_IID =
    "{b6b957e6-1dd1-11b2-89d7-e30624f50b00}";

  public nsIMutableArray getASN1Objects();

  public void setASN1Objects(nsIMutableArray arg1);

  public boolean getIsValidContainer();

  public void setIsValidContainer(boolean arg1);

  public boolean getIsExpanded();

  public void setIsExpanded(boolean arg1);

}
