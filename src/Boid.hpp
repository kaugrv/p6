#pragma once

#include <cstdlib>
#include <vector>
#include "p6/p6.h"
#define DOCTEST_CONFIG_IMPLEMENT
#include <imgui.h>
#include "doctest/doctest.h"

class Boid {
private:
    glm::vec2 m_position;
    glm::vec2 m_velocity;
    float     m_speed;
    float     m_rotation;
    float     m_radius;

public:
    // constructors
    Boid() = default;
    explicit Boid(const glm::vec2& position, const float& speed, const float& rotation = 0., const float& radius = 0.01)
        : m_position(position), m_speed(speed), m_rotation(rotation), m_radius(radius), m_velocity(glm::vec2(cos(rotation) * speed, sin(rotation) * speed)){};

    // destructor
    ~Boid() = default;

    // getter
    glm::vec2 position() const
    {
        return m_position;
    }

    float x() const
    {
        return m_position.x;
    }
    float y() const
    {
        return m_position.y;
    }

    float speed() const
    {
        return m_speed;
    }

    glm::vec2 velocity() const
    {
        return m_velocity;
    }

    glm::vec2 direction()
    {
        return glm::normalize(m_velocity);
    }

    float rotation() const
    {
        return m_rotation;
    }

    float radius() const
    {
        return m_radius;
    }

    // setter
    void set_position(const glm::vec2& position)
    {
        m_position = position;
    };
    void set_velocity(const glm::vec2& velocity)
    {
        m_velocity = velocity;
        m_speed    = glm::length(m_velocity);
    };

    void set_speed(const float& speed)
    {
        m_speed    = speed;
        m_velocity = glm::normalize(m_velocity) * speed;
    }

    void set_direction(const glm::vec2& direction)
    {
        set_velocity(glm::normalize(direction) * m_speed);
    }

    void set_rotation(float rotation)
    {
        m_rotation = rotation;
    };
    void set_radius(float radius)
    {
        m_radius = radius;
    };

    void bounce()
    {
        if (x() > 1. || x() < -1.)
        {
            m_velocity.x *= -1.;
            std::cout << "boing" << std::endl;
        }
        if (y() > 1. || y() < -1.)
        {
            m_velocity.y *= -1.;
            std::cout << "boing" << std::endl;
        }
    }

    void update_position(float delta_time)
    {
        bounce();
        m_position += delta_time * m_velocity;
    }

    void draw(p6::Context& ctx)
    {
        ctx.square(
            p6::Center{
                x(), y()},
            p6::Radius{
                radius()},
            p6::Rotation{
                p6::Angle(m_velocity)}
        );
    }
};

static Boid generate_random_boid()
{
    return Boid(glm::vec2(p6::random::number(-0.9, 0.9), p6::random::number(-0.9, 0.9)), p6::random::number(-1., 1.), p6::random::number(0., 2 * p6::PI), 0.02);
}