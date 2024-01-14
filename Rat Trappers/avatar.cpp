#include "avatar.h"
#include "game.h"
#include "player_context.h"

using namespace rat_trappers;

Avatar::Avatar(Game& game) : AnimatedEntity(game)
{
	setImage(game.getSpriteSheet());
	addAnimationFrame("still", { 86, 5, 40, 24 });
	addAnimationFrame("explosion", { 128, 91, 45, 24 });
	addAnimationFrame("explosion", { 178, 91, 45, 24 });
	setCurrentAnimation("still");
	setX(45);
	setY(648);
	setVelocity(0.25f);
}

void Avatar::explode()
{
	setDirectionX(0.f);
	setEnabled(false);

	setCurrentAnimation("explosion");
	setAnimationStepSize(6);
	setDisappearCountdown(48);

	auto& ctx = mGame.getActivePlayerContext();
	ctx.setLives(ctx.getLives() - 1);
	ctx.setRelaunchTimer(150);
}

void Avatar::reset()
{
	setX(45);

	setEnabled(true);
	setVisible(true);

	setCurrentAnimation("still");
}