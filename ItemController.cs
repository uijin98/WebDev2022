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
        // �� �����Ӹ��� ���ݾ� �Ʒ� �������� �̵�
        transform.Translate(0, this.dropSpeed, 0);
        if (transform.position.y < -0.1f)
        {
            // �������� ���� �Ʒ��ΰ��� ������ ������ �Ҹ�
            Destroy(gameObject);
        }
    }
}