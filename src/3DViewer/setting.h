#ifndef SRC_SETTING_H_
#define SRC_SETTING_H_

#include <QCoreApplication>
#include <QSettings>
#include <QDebug>
#include <QColor>
#include <QVariant>

#include <cstdio>

#include "object.h"

namespace s21
{
    class Setting : public QSettings
    {
    public:
        static Setting &get_instance()
        {
            static Setting instance;
            instance.ReadSettings();
            return instance;
        }
        void set_settings(std::string key, int value)
        {
            settings_[key] = value;
            setValue(QString::fromStdString(key), value);
        }
        void set_settings_color(std::string key, QColor color)
        {
            color_[key] = color;
            setValue(QString::fromStdString(key), color);
        }
        std::vector<float> get_settings_color(std::string key)
        {
            QColor color =  color_[key];
            return {color.redF(), color.greenF(), color.blueF()};
        }
        int get_settings(std::string key)
        {
            return settings_[key];
        }

    private:
        std::map<std::string, int> settings_;
        std::map<std::string, QColor> color_;
        Setting() : QSettings("Sommerha", "3DViewer") {}
        Setting(const Setting &) = delete;
        Setting &operator=(const Setting &) = delete;
        void ReadSettings()
        {
            settings_.clear();
            settings_["vertex_display_method"] = this->value("vertex_display_method", 0).toInt();
            settings_["line_display_method"] = this->value("line_display_method", 0).toInt();
            settings_["point_size"] = this->value("point_size", 1).toInt();
            settings_["line_width"] = this->value("line_width", 1).toInt();
            settings_["type_of_projection"] = this->value("type_of_projection", 0).toInt();
            color_["color_back"] = this->value("color_back", QColor(Qt::black)).value<QColor>();
            color_["color_line"] = this->value("color_line", QColor(Qt::red)).value<QColor>();
            color_["color_top"] = this->value("color_top", QColor(Qt::blue)).value<QColor>();
        }
    };
}
#endif // SRC_SETTING_H_
