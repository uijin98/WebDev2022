using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class shoot_translate : MonoBehaviour
{
    float speed = 5.0f;
    float power = 500.0f;
    public GameObject ball;

    void Update()
    {
        float distance_per_frame = speed * Time.deltaTime;
        float vertical_input = Input.GetAxis("Vertical");
        float horizontal_input = Input.GetAxis("Horizontal");
        Vector3 launch_direction = new Vector3(0, 1, 1);

        transform.Translate(Vector3.forward * vertical_input * distance_per_frame);
        transform.Translate(Vector3.right * horizontal_input * distance_per_frame);

        if (Input.GetButtonDown("Fire1"))
            ball.GetComponent<Rigidbody>().AddForce(launch_direction * power);
    }
}
