extends CharacterBody2D


@export_category("Movement Parammeters")
@export var move_velocity: float = 300.0

@export_category("Jump Parameters")
@export var jump_peak_time:   float = 0.5
@export var jump_fall_time:   float = 0.5
@export var jump_height:      float = 2.0
@export var jump_buffer_time: float = 0.2

@onready var sprite: Sprite2D =  $Sprite2D

var jump_gravity: float = ProjectSettings.get_setting("physics/2d/default_gravity")
var fall_gravity: float = 50.0

var move_speed:     float = 300.0
var jump_velocity:  float = -400.0
var jump_buffer:    bool  = false
var jump_available: bool  = true


func _ready() -> void:
	_calculate_parameters()

func _process(_delta: float) -> void:
	pass

func _physics_process(delta: float) -> void:
	# Add the gravity.
	if not is_on_floor():
		if velocity.y > 0:
			velocity.y += fall_gravity * delta
		else:
			velocity.y += jump_gravity * delta

	# Handle jump.
	if Input.is_action_just_pressed("ui_accept") and is_on_floor():
		jump()

	handle_movement()


func jump() -> void:
	velocity.y = jump_velocity
	jump_available = false

func handle_movement() -> void:
	var direction := Input.get_axis("ui_left", "ui_right")

	if direction > 0:
		sprite.flip_h = false
	elif direction < 0:
		sprite.flip_h = true

	if direction:
		velocity.x = direction * move_speed
	else:
		velocity.x = move_toward(velocity.x, 0, move_speed)

	move_and_slide()

func _calculate_parameters() -> void:
	jump_gravity = (2 * jump_height)/pow(jump_peak_time, 2)
	fall_gravity = (2 * jump_height)/pow(jump_fall_time, 2)
	jump_velocity = jump_gravity * jump_peak_time * -1
