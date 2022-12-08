using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ItemGenerator : MonoBehaviour
{

    public GameObject half;
    public GameObject coke;
    public GameObject skeleton;
    public GameObject soda;
    public GameObject tangerine;
    float span = 1.0f;
    float delta = 0;
    int ratio = 2;
    float speed = -0.009f;

    public void SetParameter(float span, float speed, int ratio)
    {
        this.span = span;
        this.speed = speed;
        this.ratio = ratio;
    }

    // Update is called once per frame
    void Update()
    {
        // Time.deltaTime�� �������Ӱ� ���� �������� �ð�����
        this.delta += Time.deltaTime;
        if (this.delta > this.span)
        {
      

            this.delta = 0;
           
            // Range �޼���� ù��° �Ű� �������� ũ�� �� ��° �Ű� ���� �̸��� ������ ��ȯ
            int dice = Random.Range(0, 11);


            /*
            if (dice <= this.ratio)
            {
                
                item = Instantiate(coke) as GameObject;
                item = Instantiate(skeleton) as GameObject;
                item = Instantiate(soda) as GameObject;

            }
           
            else
            {
                item = Instantiate(half) as GameObject;
                item = Instantiate(tangerine) as GameObject;

            }
            */

            GameObject item=null;


            switch (dice){
                case 1: item = Instantiate(coke) as GameObject;
                    break;

                case 2: item = Instantiate(soda) as GameObject;
                    break;

                case 3: item = Instantiate(skeleton) as GameObject;
                    break;

                case 4: item = Instantiate(tangerine) as GameObject;
                    break;

                case 5: item = Instantiate(half) as GameObject;
                    break;

              
            }

            float x = Random.Range(17, 23); //�������� ������ x ����
            float z = Random.Range(15, 19); //�������� ������ z ����
            item.transform.position = new Vector3(x, 6, z);     //�������� ���� y ����
                         /*item.transform.position = new Vector3(x, 6, z);     //�������� ���� y ����*/
            item.GetComponent<ItemController>().dropSpeed = this.speed;
        }
    }
}