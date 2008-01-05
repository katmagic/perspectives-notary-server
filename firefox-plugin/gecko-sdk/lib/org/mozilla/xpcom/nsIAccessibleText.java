/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIAccessibleText">
 **/

package org.mozilla.xpcom;

public interface nsIAccessibleText extends nsISupports
{
  public static final String NS_IACCESSIBLETEXT_IID =
    "{e44d3fa6-9cb2-432a-8bdb-69d72b6ada00}";

  public static final int BOUNDARY_CHAR = 0;

  public static final int BOUNDARY_WORD_START = 1;

  public static final int BOUNDARY_WORD_END = 2;

  public static final int BOUNDARY_SENTENCE_START = 3;

  public static final int BOUNDARY_SENTENCE_END = 4;

  public static final int BOUNDARY_LINE_START = 5;

  public static final int BOUNDARY_LINE_END = 6;

  public static final int BOUNDARY_ATTRIBUTE_RANGE = 7;

  public static final int COORD_TYPE_SCREEN = 0;

  public static final int COORD_TYPE_WINDOW = 1;

  public int getCaretOffset();

  public void setCaretOffset(int arg1);

  public int getCharacterCount();

  public int getSelectionCount();

  public String getText(int arg1, int arg2);

  public String getTextAfterOffset(int arg1, int arg2, int[] arg3, int[] arg4);

  public String getTextAtOffset(int arg1, int arg2, int[] arg3, int[] arg4);

  public String getTextBeforeOffset(int arg1, int arg2, int[] arg3, int[] arg4);

  public char getCharacterAtOffset(int arg1);

  public nsISupports getAttributeRange(int arg1, int[] arg2, int[] arg3);

  public void getCharacterExtents(int arg1, int[] arg2, int[] arg3, int[] arg4, int[] arg5, int arg6);

  public int getOffsetAtPoint(int arg1, int arg2, int arg3);

  public void getSelectionBounds(int arg1, int[] arg2, int[] arg3);

  public void setSelectionBounds(int arg1, int arg2, int arg3);

  public void addSelection(int arg1, int arg2);

  public void removeSelection(int arg1);

}
