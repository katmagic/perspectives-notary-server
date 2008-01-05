/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+nsIDOMCanvasRenderi">
 **/

package org.mozilla.xpcom;

public interface nsIDOMCanvasRenderingContext2D extends nsISupports
{
  public static final String NS_IDOMCANVASRENDERINGCONTEXT2D_IID =
    "{15487cf4-292b-49aa-bc36-17d9099f77a7}";

  public nsIDOMHTMLCanvasElement getCanvas();

  public void save();

  public void restore();

  public void scale(float arg1, float arg2);

  public void rotate(float arg1);

  public void translate(float arg1, float arg2);

  public float getGlobalAlpha();

  public void setGlobalAlpha(float arg1);

  public String getGlobalCompositeOperation();

  public void setGlobalCompositeOperation(String arg1);

  public nsIVariant getStrokeStyle();

  public void setStrokeStyle(nsIVariant arg1);

  public nsIVariant getFillStyle();

  public void setFillStyle(nsIVariant arg1);

  public nsIDOMCanvasGradient createLinearGradient(float arg1, float arg2, float arg3, float arg4);

  public nsIDOMCanvasGradient createRadialGradient(float arg1, float arg2, float arg3, float arg4, float arg5, float arg6);

  public nsIDOMCanvasPattern createPattern(nsIDOMHTMLImageElement arg1, String arg2);

  public float getLineWidth();

  public void setLineWidth(float arg1);

  public String getLineCap();

  public void setLineCap(String arg1);

  public String getLineJoin();

  public void setLineJoin(String arg1);

  public float getMiterLimit();

  public void setMiterLimit(float arg1);

  public float getShadowOffsetX();

  public void setShadowOffsetX(float arg1);

  public float getShadowOffsetY();

  public void setShadowOffsetY(float arg1);

  public float getShadowBlur();

  public void setShadowBlur(float arg1);

  public String getShadowColor();

  public void setShadowColor(String arg1);

  public void clearRect(float arg1, float arg2, float arg3, float arg4);

  public void fillRect(float arg1, float arg2, float arg3, float arg4);

  public void strokeRect(float arg1, float arg2, float arg3, float arg4);

  public void beginPath();

  public void closePath();

  public void moveTo(float arg1, float arg2);

  public void lineTo(float arg1, float arg2);

  public void quadraticCurveTo(float arg1, float arg2, float arg3, float arg4);

  public void bezierCurveTo(float arg1, float arg2, float arg3, float arg4, float arg5, float arg6);

  public void arcTo(float arg1, float arg2, float arg3, float arg4, float arg5);

  public void arc(float arg1, float arg2, float arg3, float arg4, float arg5, boolean arg6);

  public void rect(float arg1, float arg2, float arg3, float arg4);

  public void fill();

  public void stroke();

  public void clip();

  public void drawImage();

  public void drawWindow(nsIDOMWindow arg1, int arg2, int arg3, int arg4, int arg5, String arg6);

}
