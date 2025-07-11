#include "stdafx.h"
#include "AniPlayer.h"

AniPlayer::AniPlayer(const std::string& name)
	: GameObject(name)
{
}

void AniPlayer::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void AniPlayer::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void AniPlayer::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void AniPlayer::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		Utils::SetOrigin(body, originPreset);
	}
}

void AniPlayer::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = Utils::SetOrigin(body, originPreset);
}

void AniPlayer::Init()
{
	animator.SetTarget(&body);

	animator.AddEvent("Idle", 0,
		[]()
		{
			//std::cout << "!!" << std::endl;
		}
	);

	animator.AddEvent("Idle", 0,
		[]()
		{
			//std::cout << "??" << std::endl;
		}
	);

	body.setScale({2.5f, 2.5f});
}

void AniPlayer::Release()
{
}

void AniPlayer::Reset()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;

	animator.Play("animations/idle.csv");
	SetOrigin(Origins::BC);

	currentJumpTime = 0;
}

void AniPlayer::Update(float dt)
{
	animator.Update(dt);

	float h = 0.f;
	if (isGrounded)
	{
		h = InputMgr::GetAxis(Axis::Horizontal);
		velocity.x = h * speed;
	}

	if (InputMgr::GetKey(sf::Keyboard::Space))
	{
		if (currentJumpTime < maxJumpTime)
		{
			currentJumpTime += dt;
			isGrounded = false;
			velocity.y = -300.f;

			animator.Play("animations/jump.csv");
		}
	}
	if (!isGrounded)
	{
		velocity += gravity * dt;
	}
	position += velocity * dt;
	if (position.y >= 0.f)
	{
		velocity.y = 0.f;
		position.y = 0.f;
		isGrounded = true;
		currentJumpTime = 0;
	}
	SetPosition(position);

	if (h != 0.f)
	{
		SetScale(h > 0.f ? sf::Vector2f(2.5f, 2.5f) : sf::Vector2f(- 2.5f, 2.5f));
	}

	// Ani
	if (animator.GetCurrentClipId() == "Idle")
	{
		if (h != 0.f)
		{
			animator.Play("animations/run.csv");
		}
	}
	else if (animator.GetCurrentClipId() == "Run")
	{
		if (h > 0.f && InputMgr::GetKeyDown(sf::Keyboard::A))
		{
			animator.Play("animations/stop.csv");
		}
		if (h < 0.f && InputMgr::GetKeyDown(sf::Keyboard::D))
		{
			animator.Play("animations/stop.csv");
		}
		if (h == 0.f)
		{
			animator.Play("animations/idle.csv");
		}
	}
	else if (animator.GetCurrentClipId() == "Jump" && isGrounded)
	{
		if (h == 0.f)
		{
			animator.Play("animations/idle.csv");
		}
		else
		{
			animator.Play("animations/run.csv");
		}
	}
	if (animator.GetCurrentClipId() == "Stop")
	{
		if (velocity.x < 0.3f && velocity.x > -0.3f)
		{
			animator.Play("animations/idle.csv");
		}
	}

	// Big Mario Ani
	if (animator.GetCurrentClipId() == "Big_Idle")
	{
		if (h != 0.f)
		{
			animator.Play("animations/big_run.csv");
		}
	}
	else if (animator.GetCurrentClipId() == "Big_Run")
	{
		if (h == 0.f)
		{
			animator.Play("animations/big_idle.csv");
		}
	}
	else if (animator.GetCurrentClipId() == "Big_Jump" && isGrounded)
	{
		if (h == 0.f)
		{
			animator.Play("animations/big_idle.csv");
		}
		else
		{
			animator.Play("animations/big_run.csv");
		}
	}

	// Power Mario Ani
	if (animator.GetCurrentClipId() == "Big_Idle")
	{
		if (h != 0.f)
		{
			animator.Play("animations/big_run.csv");
		}
	}
	else if (animator.GetCurrentClipId() == "Big_Run")
	{
		if (h == 0.f)
		{
			animator.Play("animations/big_idle.csv");
		}
	}
	else if (animator.GetCurrentClipId() == "Big_Jump" && isGrounded)
	{
		if (h == 0.f)
		{
			animator.Play("animations/big_idle.csv");
		}
		else
		{
			animator.Play("animations/big_run.csv");
		}
	}

}

void AniPlayer::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
