#pragma once

struct Vec2 {
	int x, y;

	Vec2 operator+(const Vec2& other) const {
		return { x + other.x, y + other.y };
	}

	Vec2 operator-(const Vec2& other) const {
		return { x - other.x, y - other.y };
	}

	Vec2 operator*(const Vec2& other) const {
		return { x * other.x, y * other.y };
	}

	Vec2 operator*(int s) const {
		return { x * s, y * s };
	}

	Vec2& operator+=(const Vec2& other) {
		x += other.x;
		y += other.y;
		return *this;
	}

	Vec2& operator-=(const Vec2& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}

};