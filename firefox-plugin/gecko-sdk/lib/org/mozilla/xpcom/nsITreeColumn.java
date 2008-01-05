/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsITreeColumn">
 **/

package org.mozilla.xpcom;

public interface nsITreeColumn extends nsISupports
{
  public static final String NS_ITREECOLUMN_IID =
    "{58a8574d-15a8-4678-99a5-e1be56104093}";

  public static final short TYPE_TEXT = 1;

  public static final short TYPE_CHECKBOX = 2;

  public static final short TYPE_PROGRESSMETER = 3;

  public nsIDOMElement getElement();

  public nsITreeColumns getColumns();

  public int getX();

  public int getWidth();

  public String getId();

  public int getIndex();

  public boolean getPrimary();

  public boolean getCycler();

  public boolean getEditable();

  public short getType();

  public nsITreeColumn getNext();

  public nsITreeColumn getPrevious();

  public void invalidate();

}
