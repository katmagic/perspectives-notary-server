/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIPrintSettings">
 **/

package org.mozilla.xpcom;

public interface nsIPrintSettings extends nsISupports
{
  public static final String NS_IPRINTSETTINGS_IID =
    "{f1094df6-ce0e-42c9-9847-2f663172c38d}";

  public static final long kInitSaveOddEvenPages = 1L;

  public static final long kInitSaveHeaderLeft = 2L;

  public static final long kInitSaveHeaderCenter = 4L;

  public static final long kInitSaveHeaderRight = 8L;

  public static final long kInitSaveFooterLeft = 16L;

  public static final long kInitSaveFooterCenter = 32L;

  public static final long kInitSaveFooterRight = 64L;

  public static final long kInitSaveBGColors = 128L;

  public static final long kInitSaveBGImages = 256L;

  public static final long kInitSavePaperSize = 512L;

  public static final long kInitSavePaperName = 1024L;

  public static final long kInitSavePaperSizeUnit = 2048L;

  public static final long kInitSavePaperSizeType = 4096L;

  public static final long kInitSavePaperData = 8192L;

  public static final long kInitSavePaperWidth = 16384L;

  public static final long kInitSavePaperHeight = 32768L;

  public static final long kInitSaveReversed = 65536L;

  public static final long kInitSaveInColor = 131072L;

  public static final long kInitSaveOrientation = 262144L;

  public static final long kInitSavePrintCommand = 524288L;

  public static final long kInitSavePrinterName = 1048576L;

  public static final long kInitSavePrintToFile = 2097152L;

  public static final long kInitSaveToFileName = 4194304L;

  public static final long kInitSavePageDelay = 8388608L;

  public static final long kInitSaveMargins = 16777216L;

  public static final long kInitSaveNativeData = 33554432L;

  public static final long kInitSavePlexName = 67108864L;

  public static final long kInitSaveShrinkToFit = 134217728L;

  public static final long kInitSaveScaling = 268435456L;

  public static final long kInitSaveColorspace = 536870912L;

  public static final long kInitSaveResolutionName = 1073741824L;

  public static final long kInitSaveDownloadFonts = 2147483648L;

  public static final long kInitSaveAll = 4294967295L;

  public static final int kPrintOddPages = 1;

  public static final int kPrintEvenPages = 2;

  public static final int kEnableSelectionRB = 4;

  public static final int kRangeAllPages = 0;

  public static final int kRangeSpecifiedPageRange = 1;

  public static final int kRangeSelection = 2;

  public static final int kRangeFocusFrame = 3;

  public static final int kJustLeft = 0;

  public static final int kJustCenter = 1;

  public static final int kJustRight = 2;

  public static final short kUseInternalDefault = 0;

  public static final short kUseSettingWhenPossible = 1;

  public static final short kPaperSizeNativeData = 0;

  public static final short kPaperSizeDefined = 1;

  public static final short kPaperSizeInches = 0;

  public static final short kPaperSizeMillimeters = 1;

  public static final short kPortraitOrientation = 0;

  public static final short kLandscapeOrientation = 1;

  public static final short kNoFrames = 0;

  public static final short kFramesAsIs = 1;

  public static final short kSelectedFrame = 2;

  public static final short kEachFrameSep = 3;

  public static final short kFrameEnableNone = 0;

  public static final short kFrameEnableAll = 1;

  public static final short kFrameEnableAsIsAndEach = 2;

  public void setPrintOptions(int arg1, boolean arg2);

  public boolean getPrintOptions(int arg1);

  public int getPrintOptionsBits();

  public void getPageSizeInTwips(int[] arg1, int[] arg2);

  public nsIPrintSettings clone_();

  public void assign(nsIPrintSettings arg1);

  public int getStartPageRange();

  public void setStartPageRange(int arg1);

  public int getEndPageRange();

  public void setEndPageRange(int arg1);

  public double getMarginTop();

  public void setMarginTop(double arg1);

  public double getMarginLeft();

  public void setMarginLeft(double arg1);

  public double getMarginBottom();

  public void setMarginBottom(double arg1);

  public double getMarginRight();

  public void setMarginRight(double arg1);

  public double getScaling();

  public void setScaling(double arg1);

  public boolean getPrintBGColors();

  public void setPrintBGColors(boolean arg1);

  public boolean getPrintBGImages();

  public void setPrintBGImages(boolean arg1);

  public short getPrintRange();

  public void setPrintRange(short arg1);

  public String getTitle();

  public void setTitle(String arg1);

  public String getDocURL();

  public void setDocURL(String arg1);

  public String getHeaderStrLeft();

  public void setHeaderStrLeft(String arg1);

  public String getHeaderStrCenter();

  public void setHeaderStrCenter(String arg1);

  public String getHeaderStrRight();

  public void setHeaderStrRight(String arg1);

  public String getFooterStrLeft();

  public void setFooterStrLeft(String arg1);

  public String getFooterStrCenter();

  public void setFooterStrCenter(String arg1);

  public String getFooterStrRight();

  public void setFooterStrRight(String arg1);

  public short getHowToEnableFrameUI();

  public void setHowToEnableFrameUI(short arg1);

  public boolean getIsCancelled();

  public void setIsCancelled(boolean arg1);

  public short getPrintFrameTypeUsage();

  public void setPrintFrameTypeUsage(short arg1);

  public short getPrintFrameType();

  public void setPrintFrameType(short arg1);

  public boolean getPrintSilent();

  public void setPrintSilent(boolean arg1);

  public boolean getShrinkToFit();

  public void setShrinkToFit(boolean arg1);

  public boolean getShowPrintProgress();

  public void setShowPrintProgress(boolean arg1);

  public String getPaperName();

  public void setPaperName(String arg1);

  public short getPaperSizeType();

  public void setPaperSizeType(short arg1);

  public short getPaperData();

  public void setPaperData(short arg1);

  public double getPaperWidth();

  public void setPaperWidth(double arg1);

  public double getPaperHeight();

  public void setPaperHeight(double arg1);

  public short getPaperSizeUnit();

  public void setPaperSizeUnit(short arg1);

  public String getPlexName();

  public void setPlexName(String arg1);

  public String getColorspace();

  public void setColorspace(String arg1);

  public String getResolutionName();

  public void setResolutionName(String arg1);

  public boolean getDownloadFonts();

  public void setDownloadFonts(boolean arg1);

  public boolean getPrintReversed();

  public void setPrintReversed(boolean arg1);

  public boolean getPrintInColor();

  public void setPrintInColor(boolean arg1);

  public int getPaperSize();

  public void setPaperSize(int arg1);

  public int getOrientation();

  public void setOrientation(int arg1);

  public String getPrintCommand();

  public void setPrintCommand(String arg1);

  public int getNumCopies();

  public void setNumCopies(int arg1);

  public String getPrinterName();

  public void setPrinterName(String arg1);

  public boolean getPrintToFile();

  public void setPrintToFile(boolean arg1);

  public String getToFileName();

  public void setToFileName(String arg1);

  public int getPrintPageDelay();

  public void setPrintPageDelay(int arg1);

  public boolean getIsInitializedFromPrinter();

  public void setIsInitializedFromPrinter(boolean arg1);

  public boolean getIsInitializedFromPrefs();

  public void setIsInitializedFromPrefs(boolean arg1);

}
