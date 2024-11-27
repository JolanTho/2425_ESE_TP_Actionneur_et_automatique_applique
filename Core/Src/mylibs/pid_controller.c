#include "mylibs/pid_controller.h"

// Initialise un PID
PIDController pid_init(float kp, float ki, float kd) {
    PIDController pid = {kp, ki, kd, 0.0f, 0.0f};
    return pid;
}

// Calcul du PID et détermination de l'alpha
float pid_compute(PIDController *pid, float setpoint, float measured, float deltaTime) {
    // Convertir la consigne (RPM) dans la plage de mesure (-200 à 200)
    float scaledSetpoint = setpoint * (200.0 / 3000.0);

    // Calcul de l'erreur
    float error = scaledSetpoint - measured;

    // Terme proportionnel
    float proportional = pid->kp * error;

    // Terme intégral
    pid->integral += error * deltaTime;
    float integral = pid->ki * pid->integral;

    // Terme dérivé
    float derivative = pid->kd * (error - pid->prevError) / deltaTime;
    pid->prevError = error;

    // Calcul de la sortie PID
    float pid_output = proportional + integral + derivative;

    // Mapping de la sortie PID vers Alpha (0-100)
    float alpha = pid_output;


    return alpha;
}
