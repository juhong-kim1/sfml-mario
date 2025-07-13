#include "stdafx.h"
#include "AniPlayer.h"
#include "HitBox.h"
#include "GroundTileMap.h"

AniPlayer::AniPlayer(const std::string& name)
	: GameObject(name)
{
}

//bool AniPlayer::CheckBorder(const sf::Vector2f pos)
//{
//	sf::FloatRect localBounds = body.getLocalBounds();
//	sf::Transformable temp;
//	temp.setPosition(pos);
//	hitBox.UpdateTransform(temp, localBounds);
//
//	sf::FloatRect wallet(300, 300, 100, 100);
//	return hitBox.rect.getGlobalBounds().intersects(wallet);
//}

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

	body.setScale({ 1.f, 1.f });
	SetPosition({ 100.f, 417.f });
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
			velocity.y = -220.f;

			animator.Play("animations/jump.csv");
		}
	}
	if (!isGrounded)
	{
		velocity += gravity * dt;
	}
	position += velocity * dt;
	//if (position.y >= 417.f)             //블럭 충돌처리 하면 수정
	//{
	//	velocity.y = 417.f;
	//	position.y = 417.f;
	//	isGrounded = true;
	//	currentJumpTime = 0;
	//}

	isWallCehck();
	isGroundedCheck();
	SetPosition(position);




	if (h != 0.f)
	{
		SetScale(h > 0.f ? sf::Vector2f(1.f, 1.f) : sf::Vector2f(- 1.f, 1.f));
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

	hitBox.UpdateTransform(body, body.getLocalBounds());

}

void AniPlayer::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitBox.Draw(window);
}

sf::FloatRect AniPlayer::GetHitBoxBottom() const
{
	sf::FloatRect globalBounds = body.getGlobalBounds();
	return sf::FloatRect(globalBounds.left +4.f, globalBounds.top + globalBounds.height -4.f, globalBounds.width -8.f, 4.f);
}

sf::FloatRect AniPlayer::GetHitBoxTop() const
{
	sf::FloatRect globalBounds = body.getGlobalBounds();

	return sf::FloatRect(globalBounds.left + 2.f, globalBounds.top, globalBounds.width - 4.f, 4.f);
}

sf::FloatRect AniPlayer::GetHitBoxLeft() const
{
	sf::FloatRect globalBounds = body.getGlobalBounds();

	return sf::FloatRect(globalBounds.left, globalBounds.top + 2.f, 4.f, globalBounds.height - 4.f);
}

sf::FloatRect AniPlayer::GetHitBoxRight() const
{
	sf::FloatRect globalBounds = body.getGlobalBounds();

	return sf::FloatRect(globalBounds.left + globalBounds.width - 4.f, globalBounds.top + 2.f, 4.f, globalBounds.height - 4.f);
}

void AniPlayer::isGroundedCheck()
{
	if (!ground)
	{
		return;
	}

	sf::FloatRect bottomBox = GetHitBoxBottom();

	if (velocity.y >= 0)
	{

		bool foundGround = false;

		for (float i = bottomBox.left; i < bottomBox.left + bottomBox.width; ++i)
		{
			if (ground->IsGroundAt({ i, bottomBox.top + bottomBox.height }))
			{
				float groundY = ground->GetGroundHeight();
				position.y = groundY;
				velocity.y = 0;
				isGrounded = true;
				currentJumpTime = 0;
				foundGround = true;
				return;
			}
		}
		if (!foundGround)
		{
			isGrounded = false;
		}

	}
}

void AniPlayer::isWallCehck()
{
	if (!ground) return;

	if (velocity.x > 0)
	{
		sf::FloatRect rightBox = GetHitBoxRight();
		if (ground->IsWallAt({ rightBox.left + rightBox.width, rightBox.top + rightBox.height / 2 }))
		{
			velocity.x = 0;
		}
	}
	else if (velocity.x < 0)
	{
		sf::FloatRect leftBox = GetHitBoxLeft();
		if (ground->IsWallAt({ leftBox.left, leftBox.top + leftBox.height / 2 }))
		{
			velocity.x = 0;
		}
	}
}
