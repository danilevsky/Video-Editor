/* GStreamer Editing Services
 * Copyright (C) 2009 Edward Hervey <edward.hervey@collabora.co.uk>
 *               2009 Nokia Corporation
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef _GES_TIMELINE_PIPELINE
#define _GES_TIMELINE_PIPELINE

#include <glib-object.h>
#include <ges/ges.h>
#include <gst/pbutils/encoding-profile.h>

G_BEGIN_DECLS

#define GES_TYPE_TIMELINE_PIPELINE ges_timeline_pipeline_get_type()

#define GES_TIMELINE_PIPELINE(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST ((obj), GES_TYPE_TIMELINE_PIPELINE, GESTimelinePipeline))

#define GES_TIMELINE_PIPELINE_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST ((klass), GES_TYPE_TIMELINE_PIPELINE, GESTimelinePipelineClass))

#define GES_IS_TIMELINE_PIPELINE(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GES_TYPE_TIMELINE_PIPELINE))

#define GES_IS_TIMELINE_PIPELINE_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE ((klass), GES_TYPE_TIMELINE_PIPELINE))

#define GES_TIMELINE_PIPELINE_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS ((obj), GES_TYPE_TIMELINE_PIPELINE, GESTimelinePipelineClass))

typedef struct _GESTimelinePipelinePrivate GESTimelinePipelinePrivate;

/**
 * GESPipelineFlags:
 * @TIMELINE_MODE_PREVIEW_AUDIO: output audio to the soundcard
 * @TIMELINE_MODE_PREVIEW_VIDEO: output video to the screen
 * @TIMELINE_MODE_PREVIEW: output audio/video to soundcard/screen (default)
 * @TIMELINE_MODE_RENDER: render timeline (forces decoding)
 * @TIMELINE_MODE_SMART_RENDER: render timeline (tries to avoid decoding/reencoding)
 *
 * The various modes the #GESTimelinePipeline can be configured to.
 */
typedef enum {
  TIMELINE_MODE_PREVIEW_AUDIO	= 1 << 0,
  TIMELINE_MODE_PREVIEW_VIDEO	= 1 << 1,
  TIMELINE_MODE_PREVIEW		= TIMELINE_MODE_PREVIEW_AUDIO | TIMELINE_MODE_PREVIEW_VIDEO,
  TIMELINE_MODE_RENDER		= 1 << 2,
  TIMELINE_MODE_SMART_RENDER	= 1 << 3
} GESPipelineFlags;

/**
 * GESTimelinePipeline:
 *
 */

struct _GESTimelinePipeline {
  /*< private >*/
  GstPipeline parent;

  GESTimelinePipelinePrivate *priv;

  /* Padding for API extension */
  gpointer _ges_reserved[GES_PADDING];
};

/**
 * GESTimelinePipelineClass:
 * @parent_class: parent class
 *
 */

struct _GESTimelinePipelineClass {
  /*< private >*/
  GstPipelineClass parent_class;

  /* Padding for API extension */
  gpointer _ges_reserved[GES_PADDING];
};

GType ges_timeline_pipeline_get_type (void);

GESTimelinePipeline* ges_timeline_pipeline_new (void);

gboolean ges_timeline_pipeline_add_timeline (GESTimelinePipeline * pipeline,
					     GESTimeline * timeline);

gboolean ges_timeline_pipeline_set_render_settings (GESTimelinePipeline *pipeline,
						    gchar * output_uri,
						    GstEncodingProfile *profile);
gboolean ges_timeline_pipeline_set_mode (GESTimelinePipeline *pipeline,
					 GESPipelineFlags mode);

GstBuffer *
ges_timeline_pipeline_get_thumbnail_buffer(GESTimelinePipeline *self, GstCaps *caps);

GstBuffer *
ges_timeline_pipeline_get_thumbnail_rgb24(GESTimelinePipeline *self,
    gint width, gint height);

gboolean
ges_timeline_pipeline_save_thumbnail(GESTimelinePipeline *self,
    int width, int height, const gchar *format, const gchar *location);

GstElement *
ges_timeline_pipeline_preview_get_video_sink (GESTimelinePipeline * self);

void
ges_timeline_pipeline_preview_set_video_sink (GESTimelinePipeline * self,
    GstElement * sink);

GstElement *
ges_timeline_pipeline_preview_get_audio_sink (GESTimelinePipeline * self);

void
ges_timeline_pipeline_preview_set_audio_sink (GESTimelinePipeline * self,
    GstElement * sink);

G_END_DECLS

#endif /* _GES_TIMELINE_PIPELINE */

