/*
** EPITECH PROJECT, 2020
** arcade
** File description:
** Utils
*/

/**
 * \file        Utils.hpp
 * \author      Amaury Lecomte - Benjamin Bourgeois - Celeste Bousseau - Jamil Ettel - Oriane Aumoitte
 * \version     2.0
 * \date        March 8 2020
 * \brief       Define some structure and enumeration
 * \details     This file defines some structures and enumeration used by the game and the graphics
 */

#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <string>

namespace arc {

    /**
     * \struct Color
     * \brief Color structure containing r, g, b and a.
     * \details This structure is transferred between IGame and IGraphical. IGraphical can choose
     * to display the entities using colors.
     */
    struct Color {
        /// Red, from 0 to 255.
        unsigned char r;
        /// Green, from 0 to 255.
        unsigned char g;
        /// Blue, from 0 to 255.
        unsigned char b;
        /// Alpha, from 0 to 255.
        unsigned char a;

        /// Compares red, green, blue and then alpha.
        /** \return true if lower or false otherwise */
        bool operator<(const Color &rhs) const {
            if (r < rhs.r)
                return true;
            if (rhs.r < r)
                return false;
            if (g < rhs.g)
                return true;
            if (rhs.g < g)
                return false;
            if (b < rhs.b)
                return true;
            if (rhs.b < b)
                return false;
            return a < rhs.a;
        }

        /// Compares red, green, blue and then alpha.
        /** \return true if greater or false otherwise */
        bool operator>(const Color &rhs) const {
            return rhs < *this;
        }

        /// Compares red, green, blue and then alpha.
        /** \return true if lower or equal or false otherwise */
        bool operator<=(const Color &rhs) const {
            return !(rhs < *this);
        }

        /// Compares red, green, blue and then alpha.
        /** \return true if greater or equal or false otherwise */
        bool operator>=(const Color &rhs) const {
            return !(*this < rhs);
        }

        /// Compares two colors.
        /** \return true if equal or false otherwise */
        bool operator==(const arc::Color &rhs) const {
            return r == rhs.r &&
                   g == rhs.g &&
                   b == rhs.b &&
                   a == rhs.a;
        }

        /// Compares two colors.
        /** \return true if not equal or false otherwise */
        bool operator!=(const arc::Color &rhs) const {
            return !(rhs == *this);
        }
    };

    /**
     * \enum Orientation
     * \brief Entity orientation
     *
     * This enum is used by Entity to indicate the orientation of its sprite
     */
    enum Orientation {
        UP, /*!< Orientation by default. All images must UP by default */
        RIGHT, /*!< 90° RIGHT */
        DOWN, /*!< 180° RIGHT */
        LEFT, /*!< 90° LEFT */
    };

    /**
     * \enum EntityType
     * \brief Type of the entity
     *
     * This enumeration is used in Entity. It describes it's type.
     */
    enum EntityType {
        PLAYER,
        ENEMY,
        OBSTACLE,
        CONSUMABLE,
        OTHER,
    };

    /**
     * \struct Entity
     * \brief Entities are used by IGame to describe what should be displayed.
     *
     * Entities are passed from IGame to IGraphical through the Core. They contain information (e.g. position, type, color, sprite, etc.)
     * to describe the entity that the Game wishes to display.
     */
    struct Entity {

        /// Entity constructor.

        /// It initializes the ID of the entity so that each entity has a unique id in a session.
        Entity() {
            static int _id = 0;

            id = _id++;
        }

        /// Path to the sprite that should be displayed.
        std::string spritePath;
        /// Orientation of the sprite.
        Orientation orientation;

        /// If sprites cannot be displayed, this color should be displayed.
        Color backgroundColor;

        /// The type of the entity.
        EntityType type;

        /// Horizontal position of the entity in the game map.
        float x;
        /// Vertical position of the entity in the game map.
        float y;

        /// Unique ID of the Entity.
        int id;

        /// Compares two entities' IDs.
        /** \return true if the IDs are similar, false otherwise */
        bool operator==(const Entity &rhs) const {
            return (id == rhs.id);
        }

        /// Compares two entities' IDs.
        /** \return true if the IDs are different, false otherwise */
        bool operator!=(const Entity &rhs) const {
            return !(rhs == *this);
        }
    };

    /**
     * \namespace Event
     * \brief Namespace containing two enumerations.
     * \details This namespace contains enum Key and enum Type. These are used to describe events.
     */
    namespace Event {
        /**
         * \enum Key
         * \brief Enumeration for all the keys.
         * \details These are the keys that graphical libraries should implement, and that games can use.
         */
        enum Key {
            NONE,
            UNKNOWN,
            A,
            B,
            C,
            D,
            E,
            F,
            G,
            H,
            I,
            J,
            K,
            L,
            M,
            N,
            O,
            P,
            Q,
            R,
            S,
            T,
            U,
            V,
            W,
            X,
            Y,
            Z,
            RETURN,
            PAUSE,
            BACKSPACE,
            TAB,
            ESCAPE,
            ENTER,
            DELETE,
            UP,
            DOWN,
            LEFT,
            RIGHT,
            INSERT,
            HOME,
            END,
            PAGEUP,
            PAGEDOWN,
            F1,
            F2,
            F3,
            F4,
            F5,
            F6,
            F7,
            F8,
            F9,
            F10,
            F11,
            F12,
            F13,
            F14,
            F15,
            MOUSE_1,
            MOUSE_2,
            MOUSE_3,
            NUM1,
            NUM2,
            NUM3,
            NUM4,
            NUM5,
            NUM6,
            NUM7,
            NUM8,
            NUM9,
            NUM0,
        };

        /**
         * \enum Type
         * \brief Enumeration for all the event types.
         * \details These are the event types that graphical libraries should implement, and that games can use.
         */
        enum Type {
            NO_EVENT,
            MOUSE_PRESSED,
            MOUSE_RELEASED,
            MOUSE_WHEEL,
            KEY_PRESSED,
            KEY_RELEASED,
            QUIT,
            RESIZE,
        };

    }
}

#endif /* UTILS_HPP_ */
