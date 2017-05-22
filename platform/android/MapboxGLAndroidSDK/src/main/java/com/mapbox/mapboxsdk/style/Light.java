// This file is generated. Edit android/platform/scripts/generate-style-code.js, then run `make android-style-code`.

package com.mapbox.mapboxsdk.style;

import android.support.annotation.UiThread;

import com.mapbox.mapboxsdk.style.layers.Property;
import com.mapbox.mapboxsdk.style.layers.TransitionOptions;
import com.mapbox.mapboxsdk.style.layers.PropertyValue;

/**
 * 
 *
 * @see <a href="https://www.mapbox.com/mapbox-gl-style-spec/#light>">The online documentation</a>
 */
@UiThread
public class Light {

  private long nativePtr;

  /**
   * Creates a Light.
   *
   * @param nativePtr pointer used by core
   */
  public Light(long nativePtr) {
    this.nativePtr = nativePtr;
  }

  /**
   * Set the Anchor property.
   *
   * @param anchor as String
   */
  public void setAnchor(@Property.ANCHOR String anchor) {
    nativeSetAnchor(anchor);
  }

  /**
   * Set the Position property.
   *
   * @param position as Float[]
   */
  public void setPosition(float[] position) {
    nativeSetPosition(position[0], position[1], position[2]);
  }

  /**
   * Get the Position property transition options.
   *
   * @return transition options for Float[]
   */
  public TransitionOptions getPositionTransition() {
    return nativeGetPositionTransition();
  }

  /**
   * Set the Position property transition options.
   *
   * @param options transition options for Float[]
   */
  public void setPositionTransition(TransitionOptions options) {
    nativeSetPositionTransition(options.getDuration(), options.getDelay());
  }

  /**
   * Set the Color property.
   *
   * @param color as String
   */
  public void setColor(String color) {
    nativeSetColor(color);
  }

  /**
   * Get the Color property transition options.
   *
   * @return transition options for String
   */
  public TransitionOptions getColorTransition() {
    return nativeGetColorTransition();
  }

  /**
   * Set the Color property transition options.
   *
   * @param options transition options for String
   */
  public void setColorTransition(TransitionOptions options) {
    nativeSetColorTransition(options.getDuration(), options.getDelay());
  }

  /**
   * Set the Intensity property.
   *
   * @param intensity as Float
   */
  public void setIntensity(float intensity) {
    nativeSetIntensity(intensity);
  }

  /**
   * Get the Intensity property transition options.
   *
   * @return transition options for Float
   */
  public TransitionOptions getIntensityTransition() {
    return nativeGetIntensityTransition();
  }

  /**
   * Set the Intensity property transition options.
   *
   * @param options transition options for Float
   */
  public void setIntensityTransition(TransitionOptions options) {
    nativeSetIntensityTransition(options.getDuration(), options.getDelay());
  }

  private native void nativeSetAnchor(String property);
  private native void nativeSetPosition(float posX, float posY, float posZ);
  private native TransitionOptions nativeGetPositionTransition();
  private native void nativeSetPositionTransition(long duration, long delay);
  private native void nativeSetColor(String property);
  private native TransitionOptions nativeGetColorTransition();
  private native void nativeSetColorTransition(long duration, long delay);
  private native void nativeSetIntensity(float property);
  private native TransitionOptions nativeGetIntensityTransition();
  private native void nativeSetIntensityTransition(long duration, long delay);
}