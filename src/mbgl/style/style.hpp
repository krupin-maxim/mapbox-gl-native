#pragma once

#include <mbgl/style/transition_options.hpp>
#include <mbgl/style/observer.hpp>
#include <mbgl/style/source_observer.hpp>
#include <mbgl/style/layer_observer.hpp>
#include <mbgl/style/light_observer.hpp>
#include <mbgl/style/update_batch.hpp>
#include <mbgl/renderer/render_source.hpp>
#include <mbgl/renderer/render_source_observer.hpp>
#include <mbgl/renderer/render_layer.hpp>
#include <mbgl/renderer/render_light.hpp>
#include <mbgl/text/glyph_atlas_observer.hpp>
#include <mbgl/sprite/sprite_loader_observer.hpp>
#include <mbgl/map/mode.hpp>
#include <mbgl/map/zoom_history.hpp>

#include <mbgl/util/noncopyable.hpp>
#include <mbgl/util/chrono.hpp>
#include <mbgl/util/optional.hpp>
#include <mbgl/util/feature.hpp>
#include <mbgl/util/geo.hpp>

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace mbgl {

class FileSource;
class GlyphAtlas;
class SpriteAtlas;
class SpriteLoader;
class LineAtlas;
class RenderData;
class TransformState;
class RenderedQueryOptions;
class Scheduler;
class UpdateParameters;

namespace style {

class Layer;
class QueryParameters;

class Style : public GlyphAtlasObserver,
              public SpriteLoaderObserver,
              public SourceObserver,
              public RenderSourceObserver,
              public LayerObserver,
              public LightObserver,
              public util::noncopyable {
public:
    Style(Scheduler&, FileSource&, float pixelRatio);
    ~Style() override;

    void setJSON(const std::string&);

    void setObserver(Observer*);

    bool isLoaded() const;

    void update(const UpdateParameters&);

    bool hasTransitions() const;

    std::exception_ptr getLastError() const {
        return lastError;
    }

    std::vector<const Source*> getSources() const;
    std::vector<Source*> getSources();
    Source* getSource(const std::string& id) const;
    void addSource(std::unique_ptr<Source>);
    std::unique_ptr<Source> removeSource(const std::string& sourceID);

    std::vector<const Layer*> getLayers() const;
    std::vector<Layer*> getLayers();
    Layer* getLayer(const std::string& id) const;
    Layer* addLayer(std::unique_ptr<Layer>,
                    optional<std::string> beforeLayerID = {});
    std::unique_ptr<Layer> removeLayer(const std::string& layerID);

    // Should be moved to Impl eventually
    std::vector<const RenderLayer*> getRenderLayers() const;
    std::vector<RenderLayer*> getRenderLayers();
    RenderLayer* getRenderLayer(const std::string& id) const;

    std::string getName() const;
    LatLng getDefaultLatLng() const;
    double getDefaultZoom() const;
    double getDefaultBearing() const;
    double getDefaultPitch() const;

    TransitionOptions getTransitionOptions() const;
    void setTransitionOptions(const TransitionOptions&);

    void setLight(std::unique_ptr<Light>);
    Light* getLight() const;
    const RenderLight& getRenderLight() const;

    const style::Image* getImage(const std::string&) const;
    void addImage(std::unique_ptr<style::Image>);
    void removeImage(const std::string&);

    RenderData getRenderData(MapDebugOptions, float angle) const;

    std::vector<Feature> queryRenderedFeatures(const ScreenLineString& geometry,
                                               const TransformState& transformState,
                                               const RenderedQueryOptions& options) const;

    void setSourceTileCacheSize(size_t);
    void onLowMemory();

    void dumpDebugLogs() const;

    Scheduler& scheduler;
    FileSource& fileSource;
    std::unique_ptr<GlyphAtlas> glyphAtlas;
    std::unique_ptr<SpriteLoader> spriteLoader;
    std::unique_ptr<SpriteAtlas> spriteAtlas;
    std::unique_ptr<LineAtlas> lineAtlas;

    RenderSource* getRenderSource(const std::string& id) const;

private:
    std::vector<std::unique_ptr<Source>> sources;
    std::vector<std::unique_ptr<Layer>> layers;
    TransitionOptions transitionOptions;
    std::unique_ptr<Light> light;

    // Defaults
    std::string name;
    LatLng defaultLatLng;
    double defaultZoom = 0;
    double defaultBearing = 0;
    double defaultPitch = 0;

    std::vector<Immutable<Source::Impl>> sourceImpls;
    std::vector<Immutable<Layer::Impl>> layerImpls;

    std::unordered_map<std::string, std::unique_ptr<RenderSource>> renderSources;
    std::unordered_map<std::string, std::unique_ptr<RenderLayer>> renderLayers;
    RenderLight renderLight;

    std::vector<std::unique_ptr<Layer>>::const_iterator findLayer(const std::string& layerID) const;

    // GlyphAtlasObserver implementation.
    void onGlyphsError(const FontStack&, const GlyphRange&, std::exception_ptr) override;

    // SpriteLoaderObserver implementation.
    std::unordered_map<std::string, std::unique_ptr<style::Image>> spriteImages;
    void onSpriteLoaded(std::vector<std::unique_ptr<Image>>&&) override;
    void onSpriteError(std::exception_ptr) override;

    // SourceObserver implementation.
    void onSourceLoaded(Source&) override;
    void onSourceChanged(Source&) override;
    void onSourceError(Source&, std::exception_ptr) override;
    void onSourceDescriptionChanged(Source&) override;
    void onTileChanged(RenderSource&, const OverscaledTileID&) override;
    void onTileError(RenderSource&, const OverscaledTileID&, std::exception_ptr) override;

    // LayerObserver implementation.
    void onLayerFilterChanged(Layer&) override;
    void onLayerVisibilityChanged(Layer&) override;
    void onLayerPaintPropertyChanged(Layer&) override;
    void onLayerDataDrivenPaintPropertyChanged(Layer&) override;
    void onLayerLayoutPropertyChanged(Layer&, const char *) override;

    // LightObserver implementation.
    void onLightChanged(const Light&) override;

    Observer nullObserver;
    Observer* observer = &nullObserver;

    std::exception_ptr lastError;

    UpdateBatch updateBatch;
    ZoomHistory zoomHistory;

public:
    bool loaded = false;
};

} // namespace style
} // namespace mbgl
