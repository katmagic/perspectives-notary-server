/**
 * NOTE: THIS IS A GENERATED FILE. PLEASE CONSULT THE ORIGINAL IDL FILE
 * FOR THE FULL DOCUMENTION AND LICENSE.
 *
 * @see <a href="http://lxr.mozilla.org/mozilla/search?string=interface+jsdIScript">
 **/

package org.mozilla.xpcom;

public interface jsdIScript extends jsdIEphemeral
{
  public static final String JSDISCRIPT_IID =
    "{a38f65ca-1dd1-11b2-95d5-ff2947e9c920}";

  public static final long FLAG_PROFILE = 1L;

  public static final long FLAG_DEBUG = 2L;

  public static final long PCMAP_SOURCETEXT = 1L;

  public static final long PCMAP_PRETTYPRINT = 2L;

  public int getVersion();

  public long getTag();

  public long getFlags();

  public void setFlags(long arg1);

  public String getFileName();

  public String getFunctionName();

  public jsdIValue getFunctionObject();

  public String getFunctionSource();

  public long getBaseLineNumber();

  public long getLineExtent();

  public long getCallCount();

  public long getMaxRecurseDepth();

  public double getMinExecutionTime();

  public double getMaxExecutionTime();

  public double getTotalExecutionTime();

  public double getMinOwnExecutionTime();

  public double getMaxOwnExecutionTime();

  public double getTotalOwnExecutionTime();

  public void clearProfileData();

  public long pcToLine(long arg1, long arg2);

  public long lineToPc(long arg1, long arg2);

  public boolean isLineExecutable(long arg1, long arg2);

  public void setBreakpoint(long arg1);

  public void clearBreakpoint(long arg1);

  public void clearAllBreakpoints();

}
