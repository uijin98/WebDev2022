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
        // Time.deltaTime는 앞프레임과 현재 프레임의 시간차이
        this.delta += Time.deltaTime;
        if (this.delta > this.span)
        {
      

            this.delta = 0;
           
            // Range 메서드는 첫번째 매개 변수보다 크고 두 번째 매개 변수 미만의 정수를 반환
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

            float x = Random.Range(17, 23); //떨어지는 아이템 x 범위
            float z = Random.Range(15, 19); //떨어지는 아이템 z 범위
            item.transform.position = new Vector3(x, 6, z);     //떨어지는 높이 y 설정
                         /*item.transform.position = new Vector3(x, 6, z);     //떨어지는 높이 y 설정*/
            item.GetComponent<ItemController>().dropSpeed = this.speed;
        }
    }
}