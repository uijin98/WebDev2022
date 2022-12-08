using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ItemController : MonoBehaviour
{

    public float dropSpeed = -0.03f;

    // Use this for initialization
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        // 매 프레임마다 조금씩 아래 방향으로 이동
        transform.Translate(0, this.dropSpeed, 0);
        if (transform.position.y < -0.1f)
        {
            // 아이템이 무대 아래로가서 보이지 않으면 소멸
            Destroy(gameObject);
        }
    }
}