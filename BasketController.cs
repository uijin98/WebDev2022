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
        //�� ��ü�� �����̴� ��Ұ� ������ Rigidbody�� WASD �Ӹ� �ƴ϶�
        //Use gravity�� ����ؼ� �߷������� �Ǳ� ������
        //�߷¿� ���� ��ȭ�� ������ �ص־� �ϴ� ���� ������ ���� ��ġ�� ��� �����ؾ���.

        /*
        if (Input.GetKey(KeyCode.W))
        {
            playerPosition += Vector3.forward * moveSpeed * Time.deltaTime;
            //��ü�� ��ġ�� ���ŵǸ� �״��� Vector3.forward��� ������ǥ���� '��' ����, �ӵ�, �ð��� 60����1 �� ������ �� 
            //playerPosition�� �����ش�.

            myRigid.MovePosition(playerPosition);
            //���� movePosition���� ���� ���ŵ� ��ġ�� �̵��� ����.
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
            //��ü�� ��ġ�� ���ŵǸ� �״��� Vector3.forward��� ������ǥ���� '��' ����, �ӵ�, �ð��� 60����1 �� ������ �� 
            //playerPosition�� �����ش�.

            myRigid.MovePosition(playerPosition);
            //���� movePosition���� ���� ���ŵ� ��ġ�� �̵��� ����.
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