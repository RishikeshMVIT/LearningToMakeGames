extends CharacterBody2D

@onready var sprite: Sprite2D = $Sprite2D
@onready var steer_component: Node2D = $Steer

@export var max_spped: float = 200.0
@export var max_rotation: float = 50.0

func _physics_process(delta: float) -> void:
	var target = get_global_mouse_position()

	sprite.rotation = velocity.angle()

	velocity = steer_component.steer(velocity, global_position, target)

	move_and_slide()
