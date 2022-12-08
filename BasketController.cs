using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BasketController : MonoBehaviour
{
    
    public AudioClip SalamiSE;
    public AudioClip SalmonSE;
    AudioSource aud;
    

    GameObject director;

    Rigidbody myRigid;

    Vector3 playerPosition;

    static float moveSpeed = 15.0f;

    // Use this for initialization
    void Start()
    {
        myRigid = GetComponent<Rigidbody>();

        this.director = GameObject.Find("GameDirector");
        this.aud = GetComponent<AudioSource>();
    }

    void OnTriggerEnter(Collider other)
    {
        
        if (other.gameObject.tag == "coke")
        {
            
            this.director.GetComponent<GameDirector>().Getcoke();
            this.aud.PlayOneShot(this.SalamiSE);
        }

        else if (other.gameObject.tag == "skeleton")
        {
           
            this.director.GetComponent<GameDirector>().Getskeleton();
            this.aud.PlayOneShot(this.SalamiSE);
        }
        else if (other.gameObject.tag == "soda")
        {
            
            this.director.GetComponent<GameDirector>().Getsoda();
            this.aud.PlayOneShot(this.SalamiSE);
        }
        else
        {
            this.director.GetComponent<GameDirector>().Gethalf();
            this.director.GetComponent<GameDirector>().Gettangerine();
            this.aud.PlayOneShot(this.SalmonSE);
        }
        Destroy(other.gameObject);
    }


    // Update is called once per frame
    void Update()
    {
        Movement();
        
        if (Input.GetMouseButtonDown(0))
        {
            Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
            RaycastHit hit;
            if (Physics.Raycast(ray, out hit, Mathf.Infinity))
            {
                float x = Mathf.RoundToInt(hit.point.x);
                float z = Mathf.RoundToInt(hit.point.z);
                transform.position = new Vector3(x, 0.0f, z);
            }
        }
        
    }

    public void Movement()
    {
        playerPosition = this.transform.position;
        //이 물체를 움직이는 요소가 오로지 Rigidbody의 WASD 뿐만 아니라
        //Use gravity를 사용해서 중력이적용 되기 때문에
        //중력에 의한 변화도 갱신을 해둬야 하는 이유 때문에 실제 위치를 계속 적용해야함.

        /*
        if (Input.GetKey(KeyCode.W))
        {
            playerPosition += Vector3.forward * moveSpeed * Time.deltaTime;
            //물체의 위치가 갱신되면 그다음 Vector3.forward라는 세계좌표기준 '앞' 값과, 속도, 시간의 60분의1 을 곱해준 후 
            //playerPosition에 뎌해준다.

            myRigid.MovePosition(playerPosition);
            //이제 movePosition덕에 새로 갱신된 위치로 이동될 것임.
        }
        if (Input.GetKey(KeyCode.A))
        {
            playerPosition += Vector3.left * moveSpeed * Time.deltaTime;

            myRigid.MovePosition(playerPosition);
        }
        if (Input.GetKey(KeyCode.S))
        {
            playerPosition -= Vector3.forward * moveSpeed * Time.deltaTime;

            myRigid.MovePosition(playerPosition);
        }
        if (Input.GetKey(KeyCode.D))
        {
            playerPosition -= Vector3.left * moveSpeed * Time.deltaTime;

            myRigid.MovePosition(playerPosition);
        }
        */

        
        if (Input.GetKey(KeyCode.S))
        {
            playerPosition += Vector3.forward * moveSpeed * Time.deltaTime;
            //물체의 위치가 갱신되면 그다음 Vector3.forward라는 세계좌표기준 '앞' 값과, 속도, 시간의 60분의1 을 곱해준 후 
            //playerPosition에 뎌해준다.

            myRigid.MovePosition(playerPosition);
            //이제 movePosition덕에 새로 갱신된 위치로 이동될 것임.
        }
        if (Input.GetKey(KeyCode.D))
        {
            playerPosition += Vector3.left * moveSpeed * Time.deltaTime;

            myRigid.MovePosition(playerPosition);
        }
        if (Input.GetKey(KeyCode.W))
        {
            playerPosition -= Vector3.forward * moveSpeed * Time.deltaTime;

            myRigid.MovePosition(playerPosition);
        }
        if (Input.GetKey(KeyCode.A))
        {
            playerPosition -= Vector3.left * moveSpeed * Time.deltaTime;

            myRigid.MovePosition(playerPosition);
        }
        
    }
}