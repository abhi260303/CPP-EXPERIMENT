import pygame
import sys

pygame.init()

# Window dimensions
WIDTH, HEIGHT = 800, 600
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Bouncing Ball Simulation")

# Colors
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
RED = (255, 0, 0)

# Ball parameters
ball_radius = 20
ball_x = WIDTH // 2
ball_y = HEIGHT // 2
ball_x_speed = 5
ball_y_speed = 5
gravity = 0.1

clock = pygame.time.Clock()

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()

    # Update ball position
    ball_x += ball_x_speed
    ball_y += ball_y_speed

    # Apply gravity
    ball_y_speed += gravity

    # Bounce off the walls
    if ball_x - ball_radius < 0 or ball_x + ball_radius > WIDTH:
        ball_x_speed = -ball_x_speed
    if ball_y - ball_radius < 0 or ball_y + ball_radius > HEIGHT:
        ball_y_speed = -ball_y_speed

    # Clear the screen
    screen.fill(BLACK)

    # Draw the ball
    pygame.draw.circle(screen, RED, (int(ball_x), int(ball_y)), ball_radius)

    # Update the display
    pygame.display.flip()
    clock.tick(60)
