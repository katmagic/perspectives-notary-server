/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsISelectionControl">
 **/

package org.mozilla.xpcom;

public interface nsISelectionController extends nsISelectionDisplay
{
  public static final String NS_ISELECTIONCONTROLLER_IID =
    "{93aaa4a9-b78e-42eb-9d67-5de77ee2f54b}";

  public static final short SELECTION_NONE = 0;

  public static final short SELECTION_NORMAL = 1;

  public static final short SELECTION_SPELLCHECK = 2;

  public static final short SELECTION_IME_RAWINPUT = 4;

  public static final short SELECTION_IME_SELECTEDRAWTEXT = 8;

  public static final short SELECTION_IME_CONVERTEDTEXT = 16;

  public static final short SELECTION_IME_SELECTEDCONVERTEDTEXT = 32;

  public static final short SELECTION_ACCESSIBILITY = 64;

  public static final short NUM_SELECTIONTYPES = 8;

  public static final short SELECTION_ANCHOR_REGION = 0;

  public static final short SELECTION_FOCUS_REGION = 1;

  public static final short NUM_SELECTION_REGIONS = 2;

  public static final short SELECTION_OFF = 0;

  public static final short SELECTION_HIDDEN = 1;

  public static final short SELECTION_ON = 2;

  public static final short SELECTION_DISABLED = 3;

  public static final short SELECTION_ATTENTION = 4;

  public void setDisplaySelection(short arg1);

  public short getDisplaySelection();

  public nsISelection getSelection(short arg1);

  public void scrollSelectionIntoView(short arg1, short arg2, boolean arg3);

  public void repaintSelection(short arg1);

  public void setCaretEnabled(boolean arg1);

  public void setCaretReadOnly(boolean arg1);

  public boolean getCaretEnabled();

  public void setCaretVisibilityDuringSelection(boolean arg1);

  public void characterMove(boolean arg1, boolean arg2);

  public void wordMove(boolean arg1, boolean arg2);

  public void lineMove(boolean arg1, boolean arg2);

  public void intraLineMove(boolean arg1, boolean arg2);

  public void pageMove(boolean arg1, boolean arg2);

  public void completeScroll(boolean arg1);

  public void completeMove(boolean arg1, boolean arg2);

  public void scrollPage(boolean arg1);

  public void scrollLine(boolean arg1);

  public void scrollHorizontal(boolean arg1);

  public void selectAll();

  public boolean checkVisibility(nsIDOMNode arg1, short arg2, short arg3);

}
