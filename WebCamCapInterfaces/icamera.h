/*
 *
 * Copyright (C) 2015  Miroslav Krajicek (https://github.com/kaajo).
 * All Rights Reserved.
 *
 * This file is part of WebCamCap.
 *
 * WebCamCap is free software: you can redistribute it and/or modify
 * it under the terms of the GNU LGPL version 3 as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * WebCamCap is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU LGPL version 3
 * along with WebCamCap. If not, see <http://www.gnu.org/licenses/lgpl-3.0.txt>.
 *
 */

#ifndef ICAMERA_H
#define ICAMERA_H

#include "webcamcapinterfaces_global.h"

#include "line.h"
#include "camerasettings.h"

#include <opencv2/core/core.hpp>

#include <QWaitCondition>
#include <QVector>
#include <QVariantMap>
#include <QObject>

#include <memory>

class WEBCAMCAPINTERFACESSHARED_EXPORT ICamera : public QObject
{
    Q_OBJECT

protected:
    std::shared_ptr<CameraSettings> m_settings = nullptr;
    QWaitCondition *m_waitCondition = nullptr;

public:
    explicit ICamera(QObject *parent = 0);
    virtual ~ICamera();

    enum class CameraCalibrationType {
        BACKGROUND,
        THRESHOLD
    };

    virtual QVector<Line> nextFrame() = 0;
    virtual QVector<QVector3D> nextFrame2D() = 0;
    virtual void calibrate(CameraCalibrationType type) = 0;

    std::shared_ptr<CameraSettings> settings() const;
    void setSettings(std::shared_ptr<CameraSettings> settings);
    void setWaitCondition(QWaitCondition *waitCondition);

    virtual QVariantMap toVariantMap() const = 0;
    virtual bool fromVariantMap(QVariantMap varMap) = 0;


signals:
    void imageShow(cv::Mat image);
    void results(QVector<Line>);
    void finished();

public slots:
    virtual void showPreviewInWindow(bool show) = 0;
    virtual bool turnOn(bool turnOn) = 0;
    virtual void setThreshold(size_t threshold) = 0;
    virtual void stopWork() = 0;
    virtual void startWork() = 0;

private slots:
    virtual void settingsChanged(CameraSettings::CameraSettingsType type) = 0;
};

#endif // ICAMERA_H
