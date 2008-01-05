/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIAccessibilitySer">
 **/

package org.mozilla.xpcom;

public interface nsIAccessibilityService extends nsIAccessibleRetrieval
{
  public static final String NS_IACCESSIBILITYSERVICE_IID =
    "{0e80f152-d676-4fba-8862-9dc4eb761442}";

  public nsIAccessible createOuterDocAccessible(nsIDOMNode arg1);

  public nsIAccessible createRootAccessible(nsISupports arg1, nsISupports arg2);

  public nsIAccessible createHTML4ButtonAccessible(nsISupports arg1);

  public nsIAccessible createXULAlertAccessible(nsIDOMNode arg1);

  public nsIAccessible createHTMLAreaAccessible(nsISupports arg1, nsIDOMNode arg2, nsIAccessible arg3);

  public nsIAccessible createHTMLBlockAccessible(nsISupports arg1);

  public nsIAccessible createHTMLButtonAccessible(nsISupports arg1);

  public nsIAccessible createHTMLButtonAccessibleXBL(nsIDOMNode arg1);

  public nsIAccessible createHTMLAccessibleByMarkup(nsISupports arg1, nsISupports arg2, nsIDOMNode arg3, String arg4);

  public nsIAccessible createHTMLLIAccessible(nsISupports arg1, nsISupports arg2, String arg3);

  public nsIAccessible createHTMLCheckboxAccessible(nsISupports arg1);

  public nsIAccessible createHTMLCheckboxAccessibleXBL(nsIDOMNode arg1);

  public nsIAccessible createHTMLComboboxAccessible(nsIDOMNode arg1, nsISupports arg2);

  public nsIAccessible createHTMLGenericAccessible(nsISupports arg1);

  public nsIAccessible createHTMLGroupboxAccessible(nsISupports arg1);

  public nsIAccessible createHTMLHRAccessible(nsISupports arg1);

  public nsIAccessible createHTMLImageAccessible(nsISupports arg1);

  public nsIAccessible createHTMLLabelAccessible(nsISupports arg1);

  public nsIAccessible createHTMLListboxAccessible(nsIDOMNode arg1, nsISupports arg2);

  public nsIAccessible createHTMLObjectFrameAccessible(nsISupports arg1);

  public nsIAccessible createHTMLRadioButtonAccessible(nsISupports arg1);

  public nsIAccessible createHTMLRadioButtonAccessibleXBL(nsIDOMNode arg1);

  public nsIAccessible createHTMLSelectOptionAccessible(nsIDOMNode arg1, nsIAccessible arg2, nsISupports arg3);

  public nsIAccessible createHTMLTableAccessible(nsISupports arg1);

  public nsIAccessible createHTMLTableCellAccessible(nsISupports arg1);

  public nsIAccessible createHTMLTableCaptionAccessible(nsIDOMNode arg1);

  public nsIAccessible createHTMLTableHeadAccessible(nsIDOMNode arg1);

  public nsIAccessible createHTMLTextAccessible(nsISupports arg1);

  public nsIAccessible createHTMLTextFieldAccessible(nsISupports arg1);

  public nsIAccessible createXULButtonAccessible(nsIDOMNode arg1);

  public nsIAccessible createXULCheckboxAccessible(nsIDOMNode arg1);

  public nsIAccessible createXULColorPickerAccessible(nsIDOMNode arg1);

  public nsIAccessible createXULColorPickerTileAccessible(nsIDOMNode arg1);

  public nsIAccessible createXULComboboxAccessible(nsIDOMNode arg1);

  public nsIAccessible createXULDropmarkerAccessible(nsIDOMNode arg1);

  public nsIAccessible createXULGroupboxAccessible(nsIDOMNode arg1);

  public nsIAccessible createXULImageAccessible(nsIDOMNode arg1);

  public nsIAccessible createXULLinkAccessible(nsIDOMNode arg1);

  public nsIAccessible createXULListboxAccessible(nsIDOMNode arg1);

  public nsIAccessible createXULListitemAccessible(nsIDOMNode arg1);

  public nsIAccessible createXULMenubarAccessible(nsIDOMNode arg1);

  public nsIAccessible createXULMenuitemAccessible(nsIDOMNode arg1);

  public nsIAccessible createXULMenupopupAccessible(nsIDOMNode arg1);

  public nsIAccessible createXULMenuSeparatorAccessible(nsIDOMNode arg1);

  public nsIAccessible createXULProgressMeterAccessible(nsIDOMNode arg1);

  public nsIAccessible createXULStatusBarAccessible(nsIDOMNode arg1);

  public nsIAccessible createXULRadioButtonAccessible(nsIDOMNode arg1);

  public nsIAccessible createXULRadioGroupAccessible(nsIDOMNode arg1);

  public nsIAccessible createXULSelectOptionAccessible(nsIDOMNode arg1);

  public nsIAccessible createXULSelectListAccessible(nsIDOMNode arg1);

  public nsIAccessible createXULTabAccessible(nsIDOMNode arg1);

  public nsIAccessible createXULTabBoxAccessible(nsIDOMNode arg1);

  public nsIAccessible createXULTabPanelsAccessible(nsIDOMNode arg1);

  public nsIAccessible createXULTabsAccessible(nsIDOMNode arg1);

  public nsIAccessible createXULTextAccessible(nsIDOMNode arg1);

  public nsIAccessible createXULTextBoxAccessible(nsIDOMNode arg1);

  public nsIAccessible createXULTreeAccessible(nsIDOMNode arg1);

  public nsIAccessible createXULTreeColumnsAccessible(nsIDOMNode arg1);

  public nsIAccessible createXULTreeColumnitemAccessible(nsIDOMNode arg1);

  public nsIAccessible createXULToolbarAccessible(nsIDOMNode arg1);

  public nsIAccessible createXULToolbarSeparatorAccessible(nsIDOMNode arg1);

  public nsIAccessible createXULTooltipAccessible(nsIDOMNode arg1);

}
